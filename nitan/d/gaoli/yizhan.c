// Room: /d/city/yizhan.c

inherit ROOM;

void create()
{
        set("short", "驛站");
        set("long", @LONG
這是高麗驛站，戰時負責傳送和前線裡的往來公文。因為暫時還不
開放給百姓使用，所以沒什麼可參觀的。不過這裡高麗弟子平時休息的
地方。面前的桌子上放了幾個打糕，還有幾碗清水。
LONG
        );

        set("exits", ([
                "south" : __DIR__"qinglong-2",
        ]));
        
    set("no_fight",1);
        set("resource/water",1);
        setup();
        replace_program(ROOM);
}

