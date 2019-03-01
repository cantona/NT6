inherit ROOM;
/*
string go_enter(object me)
{
        if( query_temp("been_recommend_to_yaowang", me )
         || (query("family/family_name", me) == "藥王谷") )
                return __DIR__"gd2";
        else
                return __DIR__"gd1";
}
//不知道為什麼不能用這類語句。
string go_out(object me)
{
        if( query("family/family_name", me) == "藥王谷" )
                return __DIR__"gd1";
        else
                return __DIR__"shulin/exit";
}
*/
void create()
{
        set("short", "獨木橋");
        set("long", @LONG
這是一座原木綁成的小橋，人走在上面吱吱嘎嘎的亂響，好
像隨時都會倒塌，讓人提心吊膽。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"gd2",
  "south" : __DIR__"gd1",
]));

        set("outdoors", "yaowang");
        setup();
}
