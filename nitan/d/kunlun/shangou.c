// Room: /d/kunlun/shangou.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "山溝");
        set("long", @LONG
山壁之下的一條小山溝，往西是一片稍矮的山壁，其餘三面山壁直
接雲天。這裏綠草叢生，有許多雪中之雞出沒其中。
LONG        );
        set("outdoors", "hongmei");
        set("exits", ([ /* sizeof() == 1 */
                "westup" : __DIR__"shanbi",
        ]));
        set("objects",([
                __DIR__"npc/xueji" : 2,
        ]));
        setup();
        set("coor/x", -98000);
        set("coor/y", 20050);
        set("coor/z", 40);
        replace_program(ROOM);
}