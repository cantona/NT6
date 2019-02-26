// 上古十大神器之 崑崙鏡
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

// 可穿梭的地點
mapping place = ([
        "beijing"   : "/d/beijing/majiu",
        "yangzhou"  : "/d/city/majiu",
        "dali"      : "/d/dali/majiu",
        "foshan"    : "/d/foshan/majiu",
        "fuzhou"    : "/d/fuzhou/majiu",
        "guanwai"   : "/d/guanwai/majiu",
        "hangzhou"  : "/d/hangzhou/majiu",
        "lanzhou"   : "/d/lanzhou/majiu",
        "lingzhou"  : "/d/lingzhou/majiu",
        "luoyang"   : "/d/luoyang/majiu",
        "yongdeng"  : "/d/huanghe/majiu",
        "suzhou"    : "/d/suzhou/majiu",
        "xiangyang" : "/d/xiangyang/majiu",
        "yili"      : "/d/xingxiu/majiu",
        "chengdu"   : "/d/city3/majiu",
        "emei"      : "/d/emei/majiu1",
        "emei2"     : "/d/emei/majiu2",
        "quanzhou"  : "/d/quanzhou/majiu1",
        "jiaxing"   : "/d/quanzhou/majiu2",
        "jingzhou"  : "/d/jingzhou/majiu",
        "nanyang"   : "/d/shaolin/majiu1",
        "changan"   : "/d/changan/majiu",
        "wugong"    : "/d/quanzhen/majiu",
        "hengyang"  : "/d/henshan/majiu",
        "kaifeng"   : "/d/kaifeng/majiu",
        "kunming"   : "/d/kunming/majiu",
        "zhongzhou" : "/d/zhongzhou/majiu",

]);

void create()
{
        set_name(HIW "崑崙鏡" NOR, ({ "kunlun jing", "kunlun", "jing" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "面");
                set("long", HIW "這是一面通體銀光的鏡子，據説擁有穿梭時空的能力。\n"                               
                                "可借用其穿梭(trans)到各大城市馬廄，可以輸入 trans 查看\n"
                                "可穿梭的地點，使用 trans ? 查看使用次數。\n" NOR);                

        }

        setup();
}

void init()
{
        add_action("do_trans", "trans");
}

int do_trans(string arg)
{
        object me;
        string *places;
        int i;
        
        me = this_player();
        
        if(! objectp(present("kunlun jing", me)))return 0;
                
        places = keys(place);
        if (! arg)
        {
              write(HIC "你可以穿梭到以下地點：\n");
              for (i = 0; i < sizeof(places); i ++)
                      write(places[i] + "\n");
              
              return 1;
        }
        if (arg == "?")
        {
                 write(HIG "使用次數 " + this_object()->query("count") + "/30\n" NOR);
                 return 1;
        }
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
                         
        if (member_array(arg, places) == -1)
                 return notify_fail("看清楚，沒有你要到的地方。\n");                

        message_sort(HIW "\n$N" HIW "揮舞着手中的崑崙鏡，剎那間光華萬道，$N" HIW "借"
                         "着萬道光芒消失在天際 ……\n" NOR, me);

        write(HIG "你從天而下，落在了地上。\n" NOR);
        
        me->move(place[arg]);        
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 30)
        {
                write(HIW "只聽得一陣清脆的破碎聲，崑崙鏡已經損壞了！\n" NOR);
                destruct(this_object());                                
        }
        
        return 1;
}
