//ROOM: /d/yanziwu/juxian.c

inherit ROOM;

void create()
{
        set("short", "龍鳳廳");
        set("long", @LONG
這是一座氣勢巍峨，構造宏大的大廳堂，大門前一對大石獅子張
牙舞爪，廳門上「龍鳳廳」三個大字遒勁有力，氣度不凡。廳中牆上
掛滿名人字畫，一張大八仙桌上茶具齊整，四周圍着一圈檀香木大椅。
LONG );
        set("exits", ([
            "south" : __DIR__"yimen",
            "east"  : __DIR__"lixiang",
            "west"  : __DIR__"pindi"
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}