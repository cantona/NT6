// Room: /u/zqb/tiezhang/hxfang.c

inherit ROOM;

void create()
{
        set("short", "後廂房");
        set("long", @LONG
這是大廳後面的一個小房間，雖然也是巖石砌成，但是卻佈置的非常舒
適。四壁用掛毯遮住，不露一點石壁的痕跡。屋內轉圈擺放了一些椅子，上
面鋪着厚厚的軟墊，坐上去一定很舒適。這裏是幫主處理幫中日常事務的地
方。後面通向後花院。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
            "north" : __DIR__"hhyuan-1",
            "south" : __DIR__"wztang",
        ]));
         set("objects", ([
            __DIR__"npc/yahuan" : 1,
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}