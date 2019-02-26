// room-che1.c

inherit ROOM;

void create()
{
        set("short", "車爾庫的家");
        set("long", @LONG
車爾庫的帳蓬中收拾得很整潔，一張張織著紅花綠草的羊毛毯掛在四
周。矮桌上放着幾個大酒碗，一個身材苗條的女孩子捧了酒漿出來笑嘻嘻
地看着你。
LONG
        );
        set("exits", ([
             "northeast" : __DIR__"hsk",
             "west" : __DIR__"caoyuan8",
             "south" : __DIR__"caoyuan8",
             "east" : __DIR__"caoyuan8",
        ]));

        set("objects", ([
                    __DIR__"npc/aman" : 1

        ]));
      
        setup();
        replace_program(ROOM);
}