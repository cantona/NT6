// mtxiaowu.c 木屋

inherit ROOM;

void create()
{
        set("short", "木屋");
        set("long", @LONG
這裡是一個很小的木屋，室中放著一些亂七八遭的家具，牆角邊
還有一張破爛的小床，有一個英俊的少年在屋內走來走去，似乎有什
麼心事，不時的發出幾聲長嘆。。。。。。 
LONG );

       set("exits", ([
           "west" : __DIR__"mtdating",
       ]));

       set("objects",([
           __DIR__"npc/shizhongyu" : 1,
       ]));

       setup();
       replace_program(ROOM);
}