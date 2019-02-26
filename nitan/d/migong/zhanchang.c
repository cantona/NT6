
//古戰場迷宮
//tomcat 
//inherit VRM_SERVER;
inherit "/adm/daemons/vrm_server";

void create()
{
	// 迷宮房間所繼承的物件的檔案名稱。
	set_inherit_room( ROOM );

	//迷宮房間裏的怪物。
	set_maze_npcs(__DIR__"npc/beast");

	//迷宮的單邊長
	set_maze_long(20);

	//入口方向(出口在對面)
	set_entry_dir("east");

	//入口與區域的連接方向
	set_link_entry_dir("east");

	//入口與區域的連接檔案名
	set_link_entry_room(__DIR__"shanlu");

	//出口與區域的連接方向
	set_link_exit_dir("west");

	//出口與區域的連接檔案名
	set_link_exit_room(__DIR__"taoyuan");

	//入口房間短描述
	set_entry_short("荒野");

	//入口房間描述
	set_entry_desc(@LONG
這裏是據説就是上古時期天神大戰的遺址，相傳遠古時期
北方的大神和南方的的大神為了爭奪主宰的權利，在這裏爆發
了一場慘烈的大戰。如今這裏已經破敗不堪，雜草叢生的荒野
之地了，不小心就可能迷失方向了.
LONG);

	//出口房間短描述
	set_exit_short("荒野");

	//出口房間描述
	set_exit_desc(@LONG
你眼前一亮，深深的吸了口氣，心想總算是出來了。四周小鳥
的鳴叫聲和風吹過樹林的沙沙聲交織成美麗的大自然的旋律。
LONG
);

	//迷宮房間的短描述
	set_maze_room_short("古戰場");

	//迷宮房間的描述，如果有多條描述，製造每個房
	//間的時候會從中隨機選擇一個。
	set_maze_room_desc(@LONG
四周越來越暗了，你膽顫心驚的象前摸索着，到處是一些
迷路人的屍體和骷髏。不時傳來一陣陣鬼哭浪嚎,好像有什麼
東西在暗中窺視着，你不由的加快了腳步。
LONG
);

	// 迷宮房間是否為户外房間？
	set_outdoors(1);
}

