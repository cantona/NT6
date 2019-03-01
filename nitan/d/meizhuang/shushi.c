inherit ROOM;

void create()
{
        set("short", "書室");
        set("long", @LONG
這裏是禿筆翁的書室，房中有一個大案，案上放着一個筆筒，筆
筒中插着幾管大小不同的毛筆，毛筆的質料也有所不同，有狼毫，有
羊毫，有豬鬃，有鼠須，還有一支世上很難見到的獺毫筆，案上平鋪
着一張四尺中堂大小的宣紙，一方端硯，一柄徽墨，一對白玉鎮紙，
一個壽山筆架，都顯出主人對書法的愛好。牆上掛滿了主人書寫的一
幅幅條幅，中堂，對聯。 
LONG );
        set("exits", ([
                "east" : __DIR__"zoulang1",
        ]));

        set("objects", ([
                CLASS_D("meizhuang") + "/tubi" : 1,
                __DIR__"obj/maobi" : 2,
                __DIR__"obj/panguanbi" : 1,
        ]));

        set("outdoors", "meizhuang");
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}