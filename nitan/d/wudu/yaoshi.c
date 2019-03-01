inherit ROOM;
string* objs = ({
        __DIR__"obj/fugu",
        __DIR__"obj/chuanxin",
        __DIR__"obj/shexinzi",
        __DIR__"obj/fugu",
        __DIR__"obj/chuanxin",
        __DIR__"obj/shexinzi",
        __DIR__"obj/qianrizui",
});

void create()
{
        set("short", "藥室");
        set("long", @LONG
這裡是五毒教存放藥品的地方，你只見十多個黑漆木櫃一字排開，
上面開著數百個的小抽屜，每個抽屜上面都整整齊齊的貼著一行標簽。
這裡存放著各種珍貴藥材，其中大多數是有毒的。旁邊一個案上放著
幾束剛採來的草藥。 
LONG);
        set("exits", ([
                "west" : __DIR__"nanyuan",
        ]));
        set("objects", ([
                objs[random(sizeof(objs))] : 1,
                objs[random(sizeof(objs))] : 1,
                __DIR__"obj/zhulou"        : 2,
        ]));

        setup();
        replace_program(ROOM);
}