inherit ROOM;
void create()
{
        set("short", "地道");
        set("long",
"黑漆漆的地道，你不知道要爬多久才能出去，彷彿前面有些亮光。回\n"
"頭看來卻看不道回去的路。\n"
);
        set("exits", ([
  "westup" : __DIR__"didao2",
]));
        set("no_magic", "1");
        setup();
}
