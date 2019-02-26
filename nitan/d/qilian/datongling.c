// Room: /d/qilian/datongling.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "大通嶺");
        set("long", @LONG
這裏就是大通嶺，為貫連南祈連山脈的緊要之處。可見山羊，野兔
奔行其間，據聞此地盛產靈芝。再往上需得漸漸手腳並用。
LONG );
        set("outdoors", "qilian");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"zhutishan",
                "southeast" : __DIR__"bulangpo2",
                "westup"    : __DIR__"niaojutai",
        ]));
        set("coor/x", -10000);
        set("coor/y", 3000);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}