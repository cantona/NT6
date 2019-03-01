inherit __DIR__"binghuodao";

void create()
{
        set("short", "神秘冰洞");
        set("long",
"這是冰火島上隱藏的一處冰洞，冰洞內冰錐縱橫，寒冷異常。\n"
);
        set("exits", ([ 
                "east"   : __DIR__"shenmibingdong2", 
                "north"   : __DIR__"shenmibingdong3",
                "south"   : __DIR__"xuanwutai",
        ]));
        
        set("outdoors", 0);
        
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/bingjiangshi");        
        setup();
}
