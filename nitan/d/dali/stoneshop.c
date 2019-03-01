//Room: /d/dali/stoneshop.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","石舖");
        set("long", @LONG
大理地段有一山石以其天然的花紋而聞名天下，那便是大名鼎鼎
的大理石。用大理石中的水墨花石制作的畫屏，其奇妙程度，使人嘆
而觀止。唐宋時代，許多官商將儒都好以大理石作家居擺設。石舖裡
人頭濟濟，敲打鑽磨之聲不絕于耳。一個白族老頭光著膀子，來回踱
著小步，指導著新伙計。
LONG );
        set("objects", ([
           "/d/dali/npc/shijiang": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/dali/taiheeast",
        ]));
	set("coor/x", -19110);
	set("coor/y", -6880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}