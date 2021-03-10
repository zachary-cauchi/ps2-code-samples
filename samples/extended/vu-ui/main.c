#include <gsToolkit.h>
#include <gsKit.h>
#include <dmaKit.h>
#include <malloc.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	u64 BlueTrans, White;

	White = GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x00,0x00);
	BlueTrans = GS_SETREG_RGBAQ(0x00,0x00,0xFF,0x40,0x00);

	GSGLOBAL *gsGlobal = gsKit_init_global();

#ifdef HAVE_LIBPNG
	GSTEXTURE zbyszek;
	u64 TexCol = GS_SETREG_RGBAQ(0x80, 0x80, 0x80, 0x80, 0x00);
#else
	printf("Error preparing textures; loader is unimplemented\n");
#endif

	// Enable transparency.
	gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

	float x = 10;
	float y = 10;
	float width = 150;
	float height = 150;

	float VHeight = gsGlobal->Height;

	dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
		    D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);

	// Initialize the DMAC
	dmaKit_chan_init(DMA_CHANNEL_GIF);

	gsKit_init_screen(gsGlobal);

	// Create a persistent white background.
	gsKit_mode_switch(gsGlobal, GS_PERSISTENT);
	gsKit_clear(gsGlobal, White);

	gsKit_set_test(gsGlobal, GS_ZTEST_ON);

	gsKit_mode_switch(gsGlobal, GS_ONESHOT);

#ifdef HAVE_LIBPNG
	zbyszek.Delayed = 1;
	if (gsKit_texture_png(gsGlobal, &zbyszek, "host:zbyszek.png") < 0)
	{
		printf("Failed to load zbyszek! What now?\n");
	}
#else
	printf("Error loading textures; loader is unimplemented\n");
#endif

	while(1)
	{
		// Move the blue rectangle along.
		if( y <= 10  && (x + width) < (gsGlobal->Width - 10))
			x+=5;
		else if( (y + height)  <  (VHeight - 10) && (x + width) >= (gsGlobal->Width - 10) )
			y+=5;
		else if( (y + height) >=  (VHeight - 10) && x > 10 )
			x-=5;
		else if( y > 10 && x <= 10 )
			y-=5;

#ifdef HAVE_LIBPNG
		gsKit_TexManager_bind(gsGlobal, &zbyszek);
		gsKit_prim_sprite_texture(gsGlobal, &zbyszek, x, y, 0.0f, 0.0f, x + width, y + height, zbyszek.Width, zbyszek.Height, 4, White);
#endif

		// Flip before exec to take advantage of DMA execution double buffering.
		gsKit_sync_flip(gsGlobal);

		gsKit_queue_exec(gsGlobal);

		gsKit_TexManager_nextFrame(gsGlobal);
	}

	return 0;
}
