//Room: /d/dali/hebian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","河邊");
        set("long",@LONG
你來到河邊，兩側山壁幾乎是直上直下，西面是一條大河自北滾
滾而來，在此折向東奔騰而去，河水洶湧，巨浪滔天，發出一陣陣駭
人的轟響。此處河谷稍窄，前面有三根粗藤條綁在一棵大樹上，另一
端跨河而過，似可攀援而過。此去向南乃是崇山峻嶺。
LONG);
        set("objects", ([
           __DIR__"npc/wshangfan": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "southup"   : __DIR__"shanlin",
            "east"      : __DIR__"heshang",
        ]));
	set("coor/x", -19210);
	set("coor/y", -6830);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}