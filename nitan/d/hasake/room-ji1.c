// room-ji1.c

inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
小屋中陳設簡陋，但桌椅整潔，打掃得乾乾淨淨。一位老人正做在氈
子上整理着碗筷。四周放了些雜物，中間的小方木著上擱了幾個瓦壺，飄
出陣陣誘人的香氣。
LONG
        );
        set("exits", ([
            
            "out" : __DIR__"room-ji",
        ]));
        
        set("objects", ([
                    __DIR__"npc/ji" : 1,
      //              __DIR__"npc/li" : 1,
        ]));

        setup();
        replace_program(ROOM);
}