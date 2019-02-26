
#include <ansi.h>
void init()
{
        object me, hero, ob, room;
        object azhu;

        me = this_player();
        room = environment(me);
        hero = present("qiao feng", room);
        azhu = present("a zhu", room);
        if( objectp(hero) && objectp(azhu) && me->query_temp("juxianzhuang_step") == 13 )
        {

                if( room->query("short") == "遊府正廳" )
                {
                        tell_object(me, HIW "喬峯見你進來便對你説道：我一會兒便要和天下英雄喝酒斷義。你是超然物外的英雄，聚賢莊的人應該不會為難你的。\n"
                                            "念我們舊日的情誼，請你千萬照顧阿朱姑娘周全。\n"
                                            "以阿朱的傷勢，難以堅持太久，只有薛神醫才救得了她。切記，切記。\n" NOR);
                        message_vision(HIW "$N端起一碗酒來，説道：“這裏眾家英雄，多有往日喬峯舊交，今日既有見疑之意，咱們乾杯絕交。\n"
                                           "哪一位朋友要殺喬某的，先來對飲一碗，從此而後，往日交情一筆勾消。我殺你不是忘恩，你殺我不算負義。\n"
                                           "天下英雄，俱為證見。\n" NOR,
                                           hero, me);
                        message_vision(HIW "斷義酒喝罷，$N躍入院子，大聲喝道：“哪一個先來決一死戰！”，頓時羣雄蜂擁而上。\n" NOR, hero, me);
                        azhu->set_leader(me);
                        hero->command("go east");
                        room = environment(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/youji");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/youju");
                        ob->move(room);
                        ob->kill_ob(hero);
                }
                else
                if( room->query("short") == "演武場" )
                {
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/xu");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/shanzheng");
                        ob->move(room);
                        ob->kill_ob(hero);
                }
                else
                if( room->query("short") == "遊府後院" )
                {
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/xuan-nan");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/xuan-ji");
                        ob->move(room);
                        ob->kill_ob(hero);
                }
                else
                {
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/haojie");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/gaibang");
                        ob->move(room);
                        ob->kill_ob(hero);
                        ob = new("/maze/juxianzhuang/npc/sengren");
                        ob->move(room);
                        ob->kill_ob(hero);
                }
        }
}
