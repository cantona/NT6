inherit ROOM;

void create()
{
        set("short", "南街廣場");
        set("long", @LONG
這裏是南街廣場了，由於靠近汴梁城中心，這裏更為繁華，西邊
是一個妓院，據説京城第一名妓『李師師』就是自那裏出名的，看着
往來買笑之人蜂擁不絕，當可知道傳言非虛也，東邊是個綢緞莊，裏
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
