#include <command.h>
inherit ROOM;

void create()
{
        set("short", "內宮通道");
        set("long", @LONG
通道兩側，自東向西依次排列着獅、獬、駱駝、象、麒麟和馬六
種石雕巨獸，各有兩對四座，共十二對二十四座，造型生動，栩栩如
生，使你像來到了傳説的仙界。在淡淡的月照下，眾石獸或蹲或立，
不畏風霜雨雪。
LONG );
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);       
        /*
        set("objects", ([
                "/maze/mausoleum/npc/jiangling": 1,  
                "/maze/mausoleum/npc/qianrenzhang": 1,
                "/maze/mausoleum/npc/bairenzhang": 2,
                "/maze/mausoleum/npc/bingshi": 3,
                "/maze/mausoleum/npc/baozi": 2,
                "/maze/mausoleum/npc/tiger": 2,
                "/maze/mausoleum/npc/lions": 1,
                "/maze/mausoleum/npc/ni": 1,
                "/maze/mausoleum/npc/mammoth": 1,
        ]));
        */
        setup();
}

void init()
{
        object me;
        string file;
        
        if( !interactive(me = this_player()) || 
            query("init_exits") ) return; 
        
        file = FUBEN_D->query_maze_dir(me); 

        set("exits/northdown", file+"northgate");
        set("exits/southdown", file+"southgate");
        set("exits/westdown",  file+"westgate");
        set("exits/eastdown",  file+"eastgate");
        set("init_exits", 1);
        tell_room(this_object(), "突然四周一陣旋轉，等一切安靜下來，你發現地板下出現幾個洞口。\n");
        LOOK_CMD->look_room(me,this_object(),query("env/brief", me));
        return;
}
