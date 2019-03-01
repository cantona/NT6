inherit ROOM;

void create()
{
        set("short", "沁芳軒");
        set("long", @LONG
這是靈鷲宮的書房，靠牆擺放著一溜書架，上面整齊地排列著各
種書籍。屋子正中是一張墨色小幾，幾上的香爐冒出縷縷輕煙，幾前
有個蒲團可供你盤坐而讀，除此外別無他物。你不由低呼，好一個雅
靜所在。
LONG );
        set("exits", ([
                "west" : __DIR__"men2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}