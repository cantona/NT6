inherit ROOM;

void create()
{
        set("short", "禪房");
        set("long", @LONG
這裡是一間安靜寬敞的禪房，乃是福壽庵中弟子打坐修行之所。
地下整整齊齊地放著許多蒲團。幾位年輕師太和俗家女弟子正肅容入
定。
LONG );
        set("exits", ([
                "west" : __DIR__"lingwenge",
        ]));
        set("sleep_room", 1);
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("coor/x", -430);
        set("coor/y", -240);
        set("coor/z", 70);
        setup();
        replace_program(ROOM);
}