inherit ROOM;

void create()
{
        set("short", "日本島");
        set("long",@LONG
深切哀悼在9·18事變中犧牲的烈士，為我們的英雄報仇吧，殺入日本島，衝啊~~
LONG);

	set("exits", ([
		"east"   : __DIR__"japan1",

	]));

   setup();

}

void init() 
{ 
    object me;
      
    me = this_player(); 
      
    set("startroom", base_name(this_object()), me);
    me->save(); 
       
} 
