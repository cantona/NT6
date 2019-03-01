// heifengdong.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "黑鳳洞");
        set("long", @LONG
此處位於終南山脈東部的太陽山上。只見山峰直上直下，像刀切
般的陡峭，只山腰上有一個碾盤子粗的石洞，不時冒出一股黑氣，怪
可怕的。往西是一片樹林。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "westup"  : __DIR__"shulin3",
        ]));

        set("coor/x", -3160);
        set("coor/y", 80);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}