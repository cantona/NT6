// Room: /t/wanjiegu/stone_room.c

inherit ROOM;
int do_give(object me, object obj, object who);

void create()
{
        set("short", "石屋");
        set("long", @LONG
一間用花崗巖砌成的房子，堅固無比。南面有一個小孔，西邊有
一張小牀，屋內光線黑暗，又有些潮濕。一人女子正坐在牀上不停地
喘氣，身上的衣服都被汗水濕透了。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"backyard",
        ]));
        set("objects", ([ /* sizeof() == 1 */
            __DIR__"npc/mu" : 1,
        ]));
//        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}