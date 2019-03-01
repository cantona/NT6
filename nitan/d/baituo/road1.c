// maco 2/17/2000

inherit ROOM;

void create()
{
        set("short", "小徑");
        set("long", @LONG
一條幽深的小徑，北面傳出「嘶嘶」的聲響。
LONG );
        set("exits", ([ 
                "north" : __DIR__"barn",
                "south" : __DIR__"sheyuan",
        ]));
        set("objects",([
                "/clone/beast/jinshe" : random(3),
                "/clone/beast/dushe"  : 1 + random(3),
                "/clone/beast/fushe"  : random(2),
                "/clone/beast/qingshe": random(2),
                "/clone/beast/wubushe": random(3),
        ]));

        set("outdoors", "baituo");
        replace_program(ROOM);
        set("coor/x", -49970);
        set("coor/y", 20080);
        set("coor/z", 30);
        setup();
}