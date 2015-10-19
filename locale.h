/*class LocaleEntry {
public:
char *nameToTranslate;
char *rusName;
};
LocaleEntry locale[1024] = {"OS Info","Informacix ob OS"};
int findLocEntry(char *nameToTranslate)
{
	int i=0;
	while(locale[i++].nameToTranslate!=nameToTranslate)
	;
	return i;
}
*/
#ifndef __LOCALE_H
#define __LOCALE_H
#define LANG_ENG 0
#define LANG_RUS 1
#define LC_NAME_OSINFO		0
#define LC_NAME_REBOOT		1
#define LC_NAME_PANIC		2
#define LC_NAME_EDITOR		3
#define LC_NAME_GREDIT		4
#define LC_NAME_GOMENU		5
#define LC_NAME_AUTHORS		6
#define LC_NAME_WPCOLOR		7
#define LC_NAME_MAINTOP		8
#define LC_NAME_MAINBOTTOM	9
#define LC_GREDITTITLE		10
#define LC_EDITORTITLE		11
#define LC_EDITORTIPS		12
#define LC_ABOUTTIPS		13
#define LC_AUTHORSTIPS1		14
#define LC_AUTHORSTIPS2		15
#define LC_AUTHORSTIPS3		16
#define LC_AUTHORSTIPS4		17
#define LC_NAME_LANG		18
#define LC_NAME_CLOCK		19
#define LC_NAME_CALC		20
#define LC_NAME_WPTIP		21
#define LC_NAME_HELP1		22
#define LC_NAME_HELP2		23
#define LC_NAME_HELP3		24
#define LC_NAME_HELP4		25
#define LC_NAME_HELP5		26
#define LC_NAME_HELP6		27
#define LC_NAME_HELP7		28
#define LC_NAME_HELP8		29
#define LC_NAME_HELP9		30
#define LC_NAME_HELP10		31
#define LC_NAME_HELP11		32
#define LC_NAME_HELP12		33
#define LC_NAME_HELP13		34
#define LC_NAME_HELP14		35
#define LC_NAME_HELP15		36
#define LC_NAME_HELP16		37
#define LC_NAME_HELP17		38
#define LC_NAME_HELP18		39
#define LC_NAME_HELP19		40
#define LC_NAME_HELP20		41
#define LC_NAME_HELP21		42
#define LC_NAME_HELP22		43
#define LC_NAME_HELP23		44
#define LC_NAME_HELP24		45
#define LC_NAME_HELP25		46
#define LC_NAME_HELP26		47
#define LC_NAME_HELP27		48
#define LC_NAME_HELP28		49
#define LC_NAME_HELP29		50
#define LC_NAME_HELP30		51
#define LC_NAME_HELP31		52
#define LC_NAME_HELP32		53
#define LC_NAME_HELP33		54
#define LC_NAME_HELP34		55
#define LC_NAME_HELP35		56
#define LC_NAME_HELP36		57
#define LC_NAME_HELP		58
#define LC_NAME_LVIEW		59

int currLang=LANG_ENG;
char *tNames[1024][2]/*={{"OS Info","Reboot","Test panic","365 Editor","365 Brush"},{"Informacix ob OS","Perezagruzka","Test paniki","365 Redaktor","KistX 365"}};*/;
void setupLocale()
{
//small 'w' is Y
/*tNames[0]={"OS Info","Reboot","Test panic","365 Editor","365 Brush"};
tNames[1]={"Informacix ob OS","Perezagruzka","Test paniki","365 Redaktor","KistX 365"};*/
/*
Main Developer   Nikita Ivanov (catnikita255)",MAGENTA,LIGHT_GREY);
	vgaWriteStr(authors.x+5,authors.y+29,"Second Developer Roman Zhikharevich (rzhikharevich)",MAGENTA,LIGHT_GREY);
	vgaWriteStr(authors.x+5,authors.y+37,"Original OS Name Igor Ivanov (igor74)",MAGENTA,LIGHT_GREY);
	vgaWriteStr(authors.x+5,authors.y+45,"Helped           Mitrofan Iskra (Monolit_Rex)",MAGENTA,LIGHT_GREY);
*/
if(currLang==LANG_ENG)
{
tNames[1][0]="OS Info";
tNames[1][1]="Reboot";
tNames[1][2]="Test panic";
tNames[1][3]="Text Editor";
tNames[1][4]="Graphics Editor";
tNames[1][5]="Go! Menu";
tNames[1][6]="Authors";
tNames[1][7]="Wallpaper color";
tNames[1][8]="OS365 Kernel 1.1, Z Window System 1.2.0.                                                                                        ";
tNames[1][9]="Press left CTRL to display main menu, or F1 to show help.                                                                       ";
tNames[1][10]="365 Brush. OS365 Office 1.0.1.";
tNames[1][11]="365 Editor. OS365 Office 1.0.1.";
tNames[1][12]="Press F5 to exit. Files cannot be saved today.";
tNames[1][13]="OS365 1.1, Z Window System 1.2.0. Press X to exit.";
tNames[1][14]="Main Developer   Nikita Ivanov (catnikita255)";
tNames[1][15]="Second Developer Roman Zhikharevich (rzhikharevich)";
tNames[1][16]="Original OS Name Igor Ivanov (igor74)";
tNames[1][17]="Helped           Mitrofan Iskra (Monolit_Rex)";
tNames[1][18]="Language";
tNames[1][19]="Clock";
tNames[1][20]="365 Calculator";
tNames[1][21]="Press 0 to F key to change the wallpaper color.";
tNames[1][22]="Thank you for getting OS365 1.1.";
tNames[1][23]="ABOUT THIS SYSTEM";
tNames[1][24]="OS365 is an operating system  written by Byte PowerSoft.";
tNames[1][25]="This is a version 1.1. Let's get started!";
tNames[1][26]="HELP";
tNames[1][27]="When the OS is booted, you will see the OS365 desktop. Now you can launch progs";
tNames[1][28]="from desktop pressing the underlined button, or read more and run the Go! Menu.";
tNames[1][29]="Go! Menu help";
tNames[1][30]="Press left CTRL, as sayed in bottom blue line. Now Go! Menu will be started.";
tNames[1][31]="Now use the arrow buttons and ENTER to move between menu entries.";
tNames[1][32]="PROGRAMS";
tNames[1][33]="There is a many programs to use. All list is: Clock, Text Editor, Graph-";
tNames[1][34]="ics Editor, OS Info, Authors, wallpaper color.";
tNames[1][35]="ALL PROGRAMS TOUR";
tNames[1][36]="Clock";
tNames[1][37]="Displays time. Currently has bugs. ESC to exit.";
tNames[1][38]="Graphics Editor";
tNames[1][39]="Use arrow keys and SPACE to draw. ESC";
tNames[1][40]="to exit.";
tNames[1][41]="Text Editor";
tNames[1][42]="Write text with Caps Lock supported. F5 to exit.";
tNames[1][43]="OS Info";
tNames[1][44]="Displaying OS information and color palette.";
tNames[1][45]="Authors";
tNames[1][46]="Showing all OS365 development and helpers team.";
tNames[1][47]="We hope that you enjoy using our software. We are trying to make it better.";
tNames[1][48]="";
tNames[1][49]="                                                        Made by OS365 Dev Team";
tNames[1][50]="                                                           and Byte PowerSoft.";
tNames[1][51]="Press Enter to exit.";
tNames[1][52]="";
tNames[1][53]="";
tNames[1][54]="";
tNames[1][55]="";
tNames[1][56]="";
tNames[1][57]="H     i     n     t          F          4";
tNames[1][58]="OS365 Help System";
tNames[1][59]="System Log Viewer";

}
else {
tNames[1][0]="Informacix ob OS";
tNames[1][1]="Perezagruzka";
tNames[1][2]="Test paniki";
tNames[1][3]="365 Redaktor";
tNames[1][4]="KistQ 365";
tNames[1][5]="MenY sistemw";
tNames[1][6]="Avtorw";
tNames[1][7]="Fonovwj risunok";
tNames[1][8]="Xdro@OS365|1.1, Okonnax sistema@Z|1.2.0.                                                                                        ";
tNames[1][9]="Naymite@CTRL|dlx vwvoda menY sistemw ili@F1|dlx pomo\\i.                                                                        ";
tNames[1][10]="KistQ 365. Ofis@OS365|1.0.1.";
tNames[1][11]="Tekstovwj redaktor@OS365|. Ofis@OS365|1.0.1.";
tNames[1][12]="Naymite@F5|dlx vwhoda.";
tNames[1][13]="Xdro@OS365|1.1, Okonnax sistema@Z|1.2.0. Naymite H dlx vwhoda.";
tNames[1][14]="Glavnwj razrabot$ik   Nikita Ivanov (@catnikita255|)";
tNames[1][15]="Vtoroj razrabot$ik    Artem Klimov (@xom4a2003|)";
tNames[1][16]="Pridumal imx          IgorQ Ivanov (@igor74|)";
tNames[1][17]="Pomogal i sdelal sajt Mitrofan Iskra (@Monolit_Rex|)";
tNames[1][18]="Xzwk";
tNames[1][19]="$asw    ";
tNames[1][20]="KalQkulXtor";
tNames[1][21]="Naymite klavi#u ot 0 do@F|dlx smenw fonovogo risunka.";
tNames[1][22]="Spasibo za vwbor@OS365|1.1.";
tNames[1][23]="Ob Wtoj sisteme";
tNames[1][24]="@OS365|Wto operacionnax sistema, razrabatwvaemax@Byte PowerSoft|.";
tNames[1][25]="Wto versix 1.1. Davajte na$nem!";
tNames[1][26]="POMO\\Q";
tNames[1][27]="Kogda OS zagruzitsx, vw uvidite rabo$ij stol. TeperQ vw smoyete zapuskatQ prog-";
tNames[1][28]="rammw, nayimax pod$erknutuY bukvu, libo ispolQzux@Go! Menu|.";
tNames[1][29]="ISPOLQZOVANIE@Go! Menu|";
tNames[1][30]="Naymite levwj@CTRL,|kak napisano na niynej sinej polose. TeperQ@Go! Menu|";
tNames[1][31]="budet zapu\\eno. IspolQzujte strelki i@ENTER|dlx vwbora programm.";
tNames[1][32]="PROGRAMMw";
tNames[1][33]="V@OS365|mnogo programm dlx raznwh celej. Polnwj spisok: Grafi$eskij redak-";
tNames[1][34]="tor, Tekstovwj redaktor, Informacix ob OS, $asw i Avtorw.";
tNames[1][35]="Grafi$eskij redaktor";
tNames[1][36]="PolQzujtesQ strelkami i probelom dlx risovanix.@ESC|dlx vwhoda.";
tNames[1][37]="$asw";
tNames[1][38]="PokazwvaYt vremx. Poka $to s bagami.@ESC|dlx vwhoda.";
tNames[1][39]="Tekstovwj redaktor";
tNames[1][40]="Vvod teksta s rabotaY\\im@Caps Lock. F5|dlx vwhoda.";
tNames[1][41]="Informacix ob OS";
tNames[1][42]="Vwvodit versiY OS. H dlx vwhoda.";
tNames[1][43]="Avtorw";
tNames[1][44]="Vwvodit vseh avtorov OS. H dlx vwhoda.";
tNames[1][45]="Mw nadeemsx, $to vam ponravitsx polQzovatQsx@OS365.|";
tNames[1][46]="";
tNames[1][47]="                                                        Sozdano@OS365 Dev Team";
tNames[1][48]="                                                           |i@Byte PowerSoft.|";
tNames[1][49]="Naymite@Enter|dlx vwhoda.";
tNames[1][50]="";
tNames[1][51]="";
tNames[1][52]="";
tNames[1][53]="";
tNames[1][54]="";
tNames[1][55]="";
tNames[1][56]="";
tNames[1][57]="";
tNames[1][58]="Pomo\\Q@OS365|";
tNames[1][59]="Sistemnwj yurnal";
}
}
#endif
