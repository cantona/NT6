//TOHTQ1.C

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裏是一條很普通的山路，路邊的樹林密集，芳草流香，草叢中
星星點點地點綴着一些白色野花，路面也越來越乾燥，遠處可見陣陣
塵土飛揚，為這山谷陡增了幾分生氣。
LONG );
        set("exits", ([
                "southwest" :__DIR__"tojmq3",
                "northeast" :__DIR__"tohtq2",
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}