inherit ROOM;

void create()
{
        set("short", "東廂走廊");
        set("long", @LONG
你走在一條走廊上，隱約可以聽到東邊傳來呼吸聲，似乎有人正
在那裡練功，北邊有一扇門，好象是虛掩著。南邊是間竹子紮就的屋
子，十分的素雅，裡面飄出一陣陣的茶香，有人輕聲細語地不知說那
些什麼，引得女孩子笑出聲來。
LONG );

            set("exits", ([
                "south" : __DIR__"chashi",
                "north" : __DIR__"xiuxishi",
                "west"  : __DIR__"donglang1",
                "east"  : __DIR__"liangongfang",
        ]));
        set("coor/x", -350);
        set("coor/y", -300);
        set("coor/z", 90);
        setup();
}