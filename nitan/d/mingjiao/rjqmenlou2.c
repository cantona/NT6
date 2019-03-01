//RJQMENLOU2.C

inherit ROOM;

void create()
{
        set("short", "門樓二層");
        set("long", @LONG
這裡是一間大石室，從石窗向外看去，整個院落一覽無余，這裡
正是一處易守難功的緊要關隘。右面有一條石梯直通樓上。
LONG );
        set("exits", ([
                "up" : __DIR__"rjqmenlou3",
                "down" : __DIR__"rjqmenlou1",
        ]));
        set("no_clean_up", 0);
//        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}