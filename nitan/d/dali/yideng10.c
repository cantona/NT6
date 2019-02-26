//Cracked by Kafei
// yideng10.c

inherit ROOM;
void create()
{
        set("short", "禪房");
        set("long", @LONG
這裏是一間內室禪房，一般是打坐入定的地方。偶爾也用來接待
佛門高僧，探討禪宗。
LONG );

        set("no_sleep_room",1);
        set("exits", ([
                "out" : __DIR__"yideng12.c",
        ]));
        set("invalid_startroom", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        object yd;
        if (objectp(yd=present("yideng dashi", environment(me)))) {
                message_vision("一燈大師對$N微微笑了笑：“你改變主意不需要我的治療了？好吧。”\n説罷轉身離開了禪房。\n", me);
                delete_temp("yideng_waitreward", me);
                yd->move("/d/dali/yideng9.c");
        }
    return ::valid_leave(me, dir);
}