#include <kernel.h>
#include <tamtypes.h>
#include <stdio.h>

#include <gif_tags.h>

#include <gs_gp.h>
#include <gs_psm.h>

#include <dma.h>
#include <dma_tags.h>

#include <draw.h>
#include <graph.h>
#include <packet2.h>

void init_gs(framebuffer_t *frame, zbuffer_t *z)
{
	// Create a framebuffer.
	frame->width = 512;
	frame->height = 512;
	frame->mask = 0;
	frame->psm = GS_PSM_32;
	frame->address = graph_vram_allocate(frame->width,frame->height, frame->psm, GRAPH_ALIGN_PAGE);

	// Disable the zbuffer.
	z->enable = 0;
	z->address = 0;
	z->mask = 0;
	z->zsm = 0;

	// Initialize the screen and tie the framebuffer to the read circuits.
	graph_initialize(frame->address,frame->width,frame->height,frame->psm,0,0);
}

void init_drawing_environment(framebuffer_t *frame, zbuffer_t *z)
{
	packet2_t *init = packet2_create(20, P2_TYPE_NORMAL, P2_MODE_NORMAL, 0);

	packet2_update(init, draw_setup_environment(init->next, 0, frame, z));
	packet2_update(init, draw_finish(init->next));

	dma_channel_send_packet2(init, DMA_CHANNEL_GIF, 0);
	dma_wait_fast();

	packet2_free(init);
}

/** Send packet which will clear our screen. */
void clear_screen(framebuffer_t *frame, zbuffer_t *z)
{
	packet2_t *clear = packet2_create(35, P2_TYPE_NORMAL, P2_MODE_NORMAL, 0);

	// Clear framebuffer without clearing the zbuffer.
	packet2_update(clear, draw_disable_tests(clear->next, 0, z));
	packet2_update(clear, draw_clear(clear->next, 0, 0, 0, frame->width, frame->height, 0, 0, 0));
	packet2_update(clear, draw_enable_tests(clear->next, 0, z));
	packet2_update(clear, draw_finish(clear->next));

	// Now send our current dma chain.
	dma_channel_send_packet2(clear, DMA_CHANNEL_GIF, 1);
	dma_wait_fast();

	// Wait for scene to finish drawing
	draw_wait_finish();

	graph_wait_vsync();

	packet2_free(clear);
}

void render()
{

	packet2_t *p = packet2_create(40, P2_TYPE_NORMAL, P2_TYPE_NORMAL, 0);

	rect_t rect;

	// Draw 20 100x100 squares from the origin point.
	for (int loop0=0;loop0<20;loop0++)
	{
		int row = loop0 % 4;
		rect.color.rgbaq = GIF_SET_RGBAQ((loop0 * 10), 0, 255 - (loop0 * 10), 0x80, 1);
		rect.v0 = (vertex_t) {loop0 * 20, row * 50 + loop0 * 10, 0};
		rect.v1 = (vertex_t) {loop0 * 20 + 100, row * 50 + loop0 * 10 + 100, 0};

		// Wait for our previous dma transfer to end.
		packet2_reset(p, 0);

		packet2_update(p, draw_rect_filled(p->next, 0, &rect));
		packet2_update(p, draw_finish(p->next));

		dma_wait_fast();
		dma_channel_send_packet2(p, DMA_CHANNEL_GIF, 0);
	}

	// Wait until the drawing is finished.
	draw_wait_finish();
	graph_wait_vsync();
	packet2_free(p);
}

int main(void)
{

	// The minimum buffers needed for single buffered rendering.
	framebuffer_t frame;
	zbuffer_t z;

	// Init GIF dma channel.
	dma_channel_initialize(DMA_CHANNEL_GIF,NULL,0);
	dma_channel_fast_waits(DMA_CHANNEL_GIF);

	// Init the GS, framebuffer, and zbuffer.
	init_gs(&frame,&z);

	// Init the drawing environment and framebuffer.
	init_drawing_environment(&frame,&z);

	// Clear the screen
	clear_screen(&frame, &z);
	clear_screen(&frame, &z);

	// Render the sample.
	render();

	// Free the vram.
	graph_vram_free(frame.address);

	// Disable output and reset the GS.
	graph_shutdown();

	// Shutdown our currently used dma channel.
	dma_channel_shutdown(DMA_CHANNEL_GIF,0);

	// Sleep
	SleepThread();

	return 0;

}
