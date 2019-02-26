//ROOM: /d/yanziwu/shuiyun.c

inherit ROOM;

void create()
{
        set("short", "水雲軒");
        set("long", @LONG
湖心的一座小小的亭台，四面環水，只有西側有一條曲橋與岸上
相連。軒中清風拂面，水波微揚，一羣羣游魚清晰可見，別有一番詩
情畫意。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
            "west" : __DIR__"jiashan",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                CLASS_D("murong") + "/murongfu" : 1,
        ]));
        setup();
        replace_program(ROOM);
}