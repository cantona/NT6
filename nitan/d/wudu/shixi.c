inherit ROOM;

void create()
{
        set("short", "石隙");
        set("long", @LONG
這裏是一道巖石的縫隙，窄得要人側身擠過。你沿着曲折的巖縫
向前摸去，四周黑漆漆的，只有腳下的砂石發出輕微的聲響。
LONG);

        set("exits", ([
                "down" : __DIR__"baidu2",
                "westdown" : __DIR__"mishi",
        ]));

        setup();
        replace_program(ROOM);
}