inherit VRM_SERVER;

void create()
{
        set_inherit_room( __DIR__"lin" );

        set_maze_long(8);

        //入口方向(出口在對面)
        set_entry_dir("south");

        //入口與區域的連接方向
        set_link_entry_dir("south");

        set_link_entry_room(__DIR__"gd1");

        set_link_exit_dir("north");

        set_link_exit_room(__DIR__"dmq");

        set_entry_short("濃密樹林");

        //入口房間描述
        set_entry_desc(@LONG
這裏是一片濃密的樹林，參天的大樹遮天蔽日，偶爾有幾縷
光線透進來。地上滿是枯枝敗葉，空氣中瀰漫着讓人不安的氣氛。
LONG
);

        //出口房間短描述
        set_exit_short("濃密樹林");

        //出口房間描述
        set_exit_desc(@LONG
這裏是一片濃密的樹林，參天的大樹遮天蔽日，偶爾有幾縷
光線透進來。地上滿是枯枝敗葉，空氣中瀰漫着讓人不安的氣氛。
LONG
);

        set_outdoors(1);

        set_valid_rooms( ({
        __DIR__"lin",
}));

        create_maze();
}

string query_my_map()
{
        return read_file(__DIR__"shulin.map");
}

