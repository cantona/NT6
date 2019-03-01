// Xiaoyao.c:  the sleeping room for Xingxiu
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "逍遙洞");
        set("long", @LONG
這裡就是星宿弟子淫樂之處。原來不過是一粗糙的石洞，後因眾星
宿弟子不斷修繕，成了方園幾百裡臭名昭著的淫窟。不知有多少牧羊女
在此暗無天日，度過余生。
    洞裡面舖了幾張臭烘烘的草墊子。墊子旁邊是一些破酒罐子。洞壁
(wall)上有些字跡。
LONG );
        set("sleep_room", "1");
        set("no_fight", "1");
        set("exits", ([
                "out" : __DIR__"shidao",
        ]));
        set("item_desc", ([
                "wall" : "星宿淫賊人人得而誅之！\n\n         哇！爽死了！\n",
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -50200);
        set("coor/y", 20220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}