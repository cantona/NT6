inherit __DIR__"binghuodao";

void create()
{
        set("short", "冰火島錢莊");
        set("long",
"這裡是冰火島的錢莊，專門為天下第一幫的玩家提供錢莊服務。\n"
);
        set("exits", ([ 
                "north"   : __DIR__"shadi", 
        ]));
        
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("binghuo", 1);           // 表示在冰火島
                
        set("no_fight", 1);     
        set("outdoors", 0);
        
        set("objects", ([
                __DIR__"npc/qianzhuang" : 1,
        ]));
                
        setup();
}
