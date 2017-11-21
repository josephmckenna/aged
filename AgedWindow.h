#ifndef __AgedWindow_h__
#define __AgedWindow_h__

#include <Xm/Xm.h>
#include "PImageWindow.h"
#include "PListener.h"
#include "PSpeaker.h"
#include "PMenu.h"
#include "TextSpec.h"

const short kLabelSize 		= 1024;
const short	kMaxLabelLines	= 64;

enum ELabelFlags {
	kLabelRun		= 0x00000001,	// rn
	kLabelEvID		= 0x00000002,	// gt
	kLabelTime		= 0x00000004,	// ti
	kLabelDate		= 0x00000008,	// da
	kLabelNhit		= 0x00000010,	// nh
	kLabelNnormal	= 0x00000020,	// no
	kLabelNowl		= 0x00000040,	// ow
	kLabelNlowGain	= 0x00000080,	// lg
	kLabelNfecd		= 0x00000100,	// fe
	kLabelNbutts	= 0x00000200,	// bu
	kLabelNneck		= 0x00000400,	// ne
	kLabelDataType	= 0x00000800,	// dt
	kLabelDataMin	= 0x00001000,	// mn
	kLabelDataMax	= 0x00002000,	// mx
	kLabelPeak		= 0x00004000,	// pk
	kLabelInt		= 0x00008000,	// in
	kLabelDiff		= 0x00010000,	// df
	kLabelTrigger	= 0x00020000,	// tr
	kLabelEvtNum	= 0x00040000,	// en
	kLabelFileName	= 0x00080000,	// fn
	kLabelFitPos	= 0x00100000,	// fp
	kLabelFitDir	= 0x00200000,	// fd
	kLabelFitRadius	= 0x00400000,	// fr
	kLabelFitTime	= 0x00800000,	// ft
	kLabelFitQuality= 0x01000000,	// fq
	kLabelNfit		= 0x02000000,	// nf
	kLabelSunDir	= 0x04000000,	// sd
	kLabelSunAngle	= 0x08000000,	// sa
	kLabelPrevTime	= 0x10000000,	// pt
	kLabelNextTime	= 0x20000000,	// nt
	kLabelSubRun	= 0x40000000	// sr
};


class AgedWindow : public PImageWindow,
				   public PListener, 
				   public PSpeaker,
				   public PMenuHandler
{
public:
			 		AgedWindow(int load_settings=1);
	virtual 		~AgedWindow();

	virtual void	UpdateSelf();
	virtual void	DoMenuCommand(int anID);
	virtual int		CheckMenuCommand(int anID, int flags);
	virtual void	Listen(int message, void *dataPt);
	virtual void    SetTitle(char *str=NULL);
	
	void			CreateWindow(int anID);
	void			ShowWindow(int id);
	void			DoWater(int update_displays);
	MenuList    *	GetPopupMenuItem(int id);
	void			SaveResources(int force_save=0);
	void			SetDumpRecords(int dump_level);
	
	void			LabelFormatChanged();
	TextSpec	  *	GetLabelText();
	int				GetLabelHeight()		{ return mLabelHeight;	}
	long			GetLabelFlags()			{ return mLabelFlags;	}
	
	void			AboutAged();
	
	static long		BuildLabelString(ImageData *data, TextSpec *aTextOut,
									 char *aLabelFormat, char *aBuffer);

private:
	void			SetHitMaskMenuToggles();
	void			MakeLabel();
	void			SetLabelDirty();
	void			WarnQuit();
	
	static void		SetupSum(ImageData *data);
	static int		GetPrecision(char *fmt, int def_prec);
	static void		FileOK(Widget w, ImageData *data, XmFileSelectionBoxCallbackStruct *call_data);
	static void		FileCancel(Widget w, ImageData *data, XmFileSelectionBoxCallbackStruct *call_data);
	static void		DestroyDialogProc(Widget w, Widget **dialogPtr, caddr_t call_data);
	static void		CancelProc(Widget w, Widget aShell, caddr_t call_data);
	static void		WarnCancelProc(Widget w, AgedWindow *win, caddr_t call_data);
	static void		WarnOKProc(Widget w, AgedWindow *win, caddr_t call_data);
	static void		WarnDestroyProc(Widget w, AgedWindow *win, caddr_t call_data);

	char			mLabelString[kLabelSize];// label for this event
	TextSpec		mLabelText[kMaxLabelLines];
	int				mLabelHeight;		// pixel height of label
	long			mLabelFlags;		// label flags
	int				mLabelDirty;		// non-zero if label needs remaking
	int				mPrintType;
	
	Widget			disp_text;
	Widget			aboutbox;			// about box
	Widget			mWarnDialog;		// warning dialog
};


#endif // __AgedWindow_h__
