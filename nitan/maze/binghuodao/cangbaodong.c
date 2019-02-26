inherit __DIR__"binghuodao";

void create()
{
        set("short", "藏寶洞");
        set("long",
"這裏是一處幽深的洞穴，四處是斷裂白骨，似乎曾經有人來過。\n"
"不知從何處傳來陣陣低沉的吼聲，令人毛骨悚然。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"shenmishandong",
        ]));
        
        set("outdoors", 0);
        
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 2);
        set("s_npc", __DIR__"npc/bianyijiutoulong");
                
        setup();
}
