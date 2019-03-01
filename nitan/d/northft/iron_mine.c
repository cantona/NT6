// iron_mine.c
// 鐵礦場

#include <mine_def.h>

inherit MINE_FIELD;

void create()
{
	set_maze_long(10);				// 礦區單邊長
	set_mine_room(__DIR__"mine_room");		// 有礦房間
	set_no_mine_room(__DIR__"no_mine_room");	// 無礦房間
	set_contain_quantity(10000000);			// 單位(兩),100萬斤
	set_contain_persent(15);			// 蘊藏比例
	set_reset_time_sect(20);			// 再生期（Game年）
	set_mine_class(IRON_MINE);			// 鐵礦
	set_entry_dir("west");				// 入口方向
	set_link_entry_dir("west");			// 入口和區域的連接方向
	set_link_entry_room(__DIR__"ftn13");		// 入口所連接區域檔案的文件名
        set_outdoors(1); 
}
