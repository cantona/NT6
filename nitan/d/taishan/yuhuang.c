// Room: /d/taishan/yuhuang.c
// Last Modified by Winder on Aug. 25 2001
// Modified by Zeratul Jan 11 2001 江湖閱歷低于10000不能見盟主

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "玉皇廟");
        set("long", @LONG
玉皇廟是處在泰山絕頂的廟觀，古稱太清宮、玉帝觀，由山門、玉
皇殿、觀日亭、望河亭、東西道房組成。山門額書“敕修玉皇頂”。正
殿內祀明代銅鑄玉皇大帝像。神龕上匾額“柴望遺風”。遠古帝王多在
此燔柴祭天，望祀山川諸神。觀前為古登封台，歷代皇帝封禪的儀式都
是在這裡舉行。台下有一無字碑，據說是漢武帝所立。
　　東南石坪寬敞，名平頂峰，上建乾坤亭，上刻“孔子小天下處”。
正中往上便是武林盟主所在之處─封禪台。
LONG );
        set("exits", ([
                "southdown" : __DIR__"nantian",
                "southeast" : __DIR__"riguan",
                "northwest" : __DIR__"zhangren",
                "east"      : __DIR__"guanriting",
                "west"      : __DIR__"wangheting",
                "up"        : __DIR__"fengchan",
        ]));
        set("objects",([
                __DIR__"npc/jiang" : 1,
                __DIR__"npc/wei-shi2" : 3,
        ]));
        set("coor/x", 30);
	set("coor/y", 310);
	set("coor/z", 210);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob1, ob2, ob3;
        string mengzhu, shangshan, fae;
        
        if(!( ob1 = find_living("mengzhu")) )
                ob1 = load_object("/adm/npc/meng-zhu");
        mengzhu=query("winner", ob1);

        if(!( ob2 = find_living("shangshan")) )
                ob2 = load_object("/adm/npc/shang-shan");
        shangshan=query("winner", ob2);

        if(!( ob3 = find_living("fae")) )
                ob3 = load_object("/adm/npc/fa-e");
        fae=query("winner", ob3);

        if( dir == "up" )
        { 
                if( userp(me) && query("score", me)<10000 )
                        return notify_fail( "盟主是不會見你這種小人物的，還是回去吧。\n" );
                if( present("jiang baisheng", environment(me)) &&
                        query("id", me) != mengzhu && 
                        query("id", me) != shangshan && 
                        query("id", me) != fae )
                        return notify_fail("江百勝伸手攔住你說道：盟主很忙，現在不見外客，你下山去吧！\n");
                else if( query("id", me) == mengzhu )
                {
                        message_vision(HIY "\n江百勝誠惶誠恐的向$N跪倒磕頭，大聲喊道：盟主萬歲，萬歲，萬萬歲！\n" NOR, me);
                }        
                else if( query("id", me) == shangshan )
                {
                        message_vision(HIY "\n江百勝畢恭畢敬的向$N拜倒喊道：賞善使者您好！ 屬下江百勝參見大人！\n" NOR, me);
                }        
                else if( query("id", me) == fae )
                {
                        message_vision(HIY "\n江百勝畢恭畢敬的向$N拜倒喊道：罰惡使者您好！ 屬下江百勝參見大人！\n" NOR, me);
                }        
        }

        return ::valid_leave(me, dir);
}