inherit __DIR__"binghuodao";

void create()
{
        set("short", "神祕山洞");
        set("long",
"這是一處神祕的洞穴，跟普通峽谷內的洞穴一樣，這裏顯得十\n"
"分寬敞，卻又異常潮濕。洞壁四周粘連着綠色的液體，陣陣低吼從\n"
"洞深處傳來，令人不寒而慄。\n"
);
        set("exits", ([ 
                "northwest"   : __DIR__"guanmulin1", 
                "southwest"   : __DIR__"guanmulin2",
                "east"   : __DIR__"cangbaodong",
        ]));
        
        set("outdoors", 0);
        
        set("n_time", 60);
        set("n_npc",1);
        set("n_max_npc", 2);
        set("s_npc", __DIR__"npc/jiutoulong");  
        setup();
}
