#include <ansi.h>
inherit "/adm/daemons/vrm_server.c";

#define ENTER_ROOM_X  0
#define ENTER_ROOM_Y  0
#define ENTER_ROOM_Z  0
 
void create() 
{ 
        set_lonely_create(1);
        
        //迷宮房間所繼承的物件的檔案名稱。 
        set_inherit_room( ROOM ); 
        
        //迷宮的單邊長 
        set_maze_long(8); 
        
        set_maze_boxs(3);
        
        //set_maze_traps(3);
                        
        //入口方向(出口在對面) 
        set_entry_dir("east"); 
                        
        //出口與區域的連接方向 
        set_link_exit_dir("west"); 
                        
        //出口與區域的連接檔案名 
        set_link_exit_room(__DIR__"leave"); 

        //以下是入口座標 
        set_link_entry_room_x(ENTER_ROOM_X); 
        set_link_entry_room_y(ENTER_ROOM_Y); 
        set_link_entry_room_z(ENTER_ROOM_Z); 
                        
        //普通房間描述
        set_maze_room_short("迷宮");
                        
        set_maze_room_desc(@LONG
這是一間寬敞的石屋，四周巨石壘就的牆壁泛出幽幽的青色光芒，兩盞青銅
燈吐出一尺高的火焰，飄忽閃爍，偶然有燈花爆裂的輕響，更令人感到窒息般的
寂靜。地上是丈許見方的青石板鋪就，房間中央一塊白色石板格外醒目，上面雕
刻着細密的圖紋，讓人不由自主的想上前查看（mazemap）一番。
LONG); 

        //入口房間短描述 
        set_entry_short("迷宮入口"); 
                        
        //入口房間描述 
        set_entry_desc(@LONG
這是一間寬敞的石屋，四周巨石壘就的牆壁泛出幽幽的青色光芒，兩盞青銅
燈吐出一尺高的火焰，飄忽閃爍，偶然有燈花爆裂的輕響，更令人感到窒息般的
寂靜。地上是丈許見方的青石板鋪就，房間中央一塊白色石板格外醒目，上面雕
刻着細密的圖紋，讓人不由自主的想上前查看（mazemap）一番。
LONG);
                        
        //出口房間短描述 
        set_exit_short("迷宮出口"); 
                        
        //出口房間描述 
        set_exit_desc(@LONG
這是一間寬敞的石屋，四周巨石壘就的牆壁泛出幽幽的青色光芒，兩盞青銅
燈吐出一尺高的火焰，飄忽閃爍，偶然有燈花爆裂的輕響，更令人感到窒息般的
寂靜。地上是丈許見方的青石板鋪就，房間中央一塊白色石板格外醒目，上面雕
刻着細密的圖紋，讓人不由自主的想上前查看（mazemap）一番。
LONG);
 
        // 迷宮限制最高進入等級
        set_remove_time(1800); 
} 


