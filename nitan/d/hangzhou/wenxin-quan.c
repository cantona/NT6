// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "問心泉");
        set("long", @LONG
問心泉躺卧在山麓的溝谷裏，濺珠噴雪，下垂若簾。有詩云：』
行到山深處，簾泉一畫圖。巖空懸百尺，澗響落千珠。春雨流通急，
秋雲滴不枯。』然而問心泉聞名的並不是它的美景，而是『問心』這
一泉名。心錯而情錯，情孽油生。上山拜月老的人，不妨在這裏飲一
掬清泉，捫心自問。是有情人終成眷屬，若錯姻緣早離早散。
LONG );

        set("outdoors", "xihu");
        set("exits", ([
                "east" : "/d/hangzhou/shandao1",
         ]));

        set("objects", ([
                "/d/hangzhou/npc/qinger": 1,
        ]));

	set("coor/x", 760);
	set("coor/y", -1990);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}