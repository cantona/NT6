//room: sheyuan.c
inherit ROOM;

void create()
{
        set("short","蛇園");
        set("long", @LONG
這裏是丐幫弟子的蛇園。丐幫弟子生活儉樸，隨地坐卧，不免常
受蛇蟲侵犯。日久天長，漸漸摸索出馴養之道。這裏遍地是蛇，牆上
也巴着蛇，屋檐上也向下垂着蛇，樹枝上也盤繞着蛇，不由你不心驚。
LONG );
        set("exits",([
                "west"  : __DIR__"pomiao",
        ]));
        set("outdoors", "yangzhoue");
        set("objects",([
                "/clone/beast/jinshe" :1,
                "/clone/beast/dushe" :1,
                "/clone/beast/fushe" :1,
                "/clone/beast/qingshe" :1,
                "/clone/beast/wubushe" :1,
        ]));
        set("coor/x", 80);
        set("coor/y", 60);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}