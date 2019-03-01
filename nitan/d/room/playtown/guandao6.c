// by 山貓ADX @ snow 99-12-4

inherit ROOM;

void create ()
{
        set("short",  "官道");
        set("long",  @LONG
這是一條寬闊筆直的官道，黃土路面，足可容得下十馬並馳。往東通向
汴樑城，附近有一個玩家村。
LONG);
        set("exits",  ([
                "south"  :  __DIR__"guandao7",
                "northeast"  :  __DIR__"guandao5",
        ]));
        set("outdoors",  1);
        setup();
        replace_program(ROOM);
}