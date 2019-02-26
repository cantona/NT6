inherit ROOM;
void create()
{
        set("short", "地道");
        set("long",
"前面終於出現一道光明，漫長的地道走到了盡頭。回頭看看來路一片\n"
"模糊。\n"
);
        set("exits", ([
        "up" : "/d/llszhuang/dynamic/jiuqu14",
]));
        set("no_magic", "1");
        setup();
}
