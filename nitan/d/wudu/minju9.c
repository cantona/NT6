inherit ROOM;

void create()
{
        set("short", "供桌下");
        set("long", @LONG
你現在蜷縮在低矮的供桌下面，四周到處都是灰塵和蜘蛛
網，稍一抬頭就會碰到桌面。這張桌子的四周都被骯髒的布簾
擋住了，你看不到外面的情況，別人也發現不了你。 
LONG);

        set("exits", ([
                "out" : __DIR__"minju7",
        ]));
        setup();
        replace_program(ROOM);
}