#include <ansi.h>

inherit VRM_SERVER;

//#define ENTER_ROOM_X  0
//#define ENTER_ROOM_Y    0
//#define ENTER_ROOM_Z    0

void create() 
{ 
        // 迷宮房間所繼承的物件的檔案名稱。 
        set_inherit_room( ROOM );  
                        
        //迷宮房間裏的怪物。 
        set_maze_npcs( ([
                "/maze/prison/npc/qiutu1": 1 + random(2),
                "/maze/prison/npc/qiutu2": 1 + random(2),
                "/maze/prison/npc/qiutu3": 1 + random(2),
                "/maze/prison/npc/jinyiwei": 1 + random(2),
        ]) );                   

        set_exit_npcs( "/maze/prison/npc/laotou" );
        //不算死亡              
        //set_no_death_room(1);
        
        //迷宮的單邊長 
        set_maze_long(8); 
                        
        //入口方向(出口在對面) 
        set_entry_dir("north"); 
                        
        //入口與區域的連接方向 
        set_link_entry_dir("north"); 
                        
        //入口與區域的連接檔案名 
        set_link_entry_room(__DIR__"enter"); 
                        
        //出口與區域的連接方向 
        set_link_exit_dir("south"); 
                        
        //出口與區域的連接檔案名 
        set_link_exit_room(__DIR__"out"); 
                        
        //以下是入口座標
        //set_link_entry_room_x(ENTER_ROOM_X);
        //set_link_entry_room_y(ENTER_ROOM_Y);
        //set_link_entry_room_z(ENTER_ROOM_Z);
                        
        //普通房間描述
        set_maze_room_short(RED "天牢" NOR);
                        
        set_maze_room_desc(@LONG
這裏黑沉沉的，即無一絲光亮，也無半分聲息。黑暗中依稀可以
看到身邊似乎有幾個人影，看到你轉過頭去，他們立刻屏住呼吸，緊
張地瞪着你。四壁摸上去冰涼，且極硬，似乎都是鋼鐵鑄成。腳邊有
一堆東西踢上去克剌剌地散了開來，細看卻是一具白得發亮的枯骨。
LONG); 
                        
        //入口房間短描述 
        set_entry_short(HIR "天牢入口" NOR); 
                        
        //入口房間描述 
        set_entry_desc(@LONG
這裏黑沉沉的，即無一絲光亮，也無半分聲息。黑暗中依稀可以
看到身邊似乎有幾個人影，看到你轉過頭去，他們立刻屏住呼吸，緊
張地瞪着你。四壁摸上去冰涼，且極硬，似乎都是鋼鐵鑄成。腳邊有
一堆東西踢上去克剌剌地散了開來，細看卻是一具白得發亮的枯骨。
LONG); 
                        
        //出口房間短描述 
        set_exit_short(HIW "天牢出口" NOR); 
                        
        //出口房間描述 
        set_exit_desc(@LONG
這裏黑沉沉的，即無一絲光亮，也無半分聲息。黑暗中依稀可以
看到身邊似乎有幾個人影，看到你轉過頭去，他們立刻屏住呼吸，緊
張地瞪着你。四壁摸上去冰涼，且極硬，似乎都是鋼鐵鑄成。腳邊有
一堆東西踢上去克剌剌地散了開來，細看卻是一具白得發亮的枯骨。
LONG); 

        // 迷宮房間是否為户外房間？ 
        // set_outdoors(1); 
        
} 


