inherit ROOM;

void create()
{
        set("short", "南街廣場");
        set("long", @LONG
這裡是南街廣場了，由于靠近汴樑城中心，這裡更為繁華，西邊
是一個妓院，據說京城第一名妓『李師師』就是自那裡出名的，看著
往來買笑之人蜂擁不絕，當可知道傳言非虛也，東邊是個綢緞莊，裡
面經營的各種布匹很受達官貴人們的青睞。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north" : __DIR__"center",
                "south" : __DIR__"nandajie1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}
