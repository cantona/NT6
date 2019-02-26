
#include <ansi.h>

#define HUA "「" MAG "虛空之痕" NOR "」"

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        object landie;
        object *obs, wanjia, env;
        string msg;
        
        if (! objectp(me))return 1;
        
        // 只有劍靈可以用
        if (base_name(me) != "/kungfu/class/misc/jianling")
                return notify_fail("你所使用的外功中沒有這個功能。\n");

        // 藍蝶仙子還存在時候不能用
        landie=query("mylandie", me);
        if (objectp(landie))return 1;
        
        // 距離上次藍蝶消失不足3分鐘無法施展
        if( query("first_landie", me))//已經召喚過藍蝶才受此限制
        {
                if( time()-query("last_summon_landie", me)<180 )
                        return 1; 
        }

        msg = HIC "$N" HIC "深吸一口氣，手中藍蝶寶劍頓時光芒暴現，在天空劃出一道美麗的弧線 ……"
              "頓時，天空之中撕開一條裂縫，猶如女媧補天時的虛空之痕！一道藍光從裂縫中蔓出，萬千"
              "光芒籠罩，一位美麗的仙子從天而降，守護着劍靈！\n" NOR;

        // 記錄本次是否是第一次召喚藍蝶
        if( !query("first_landie", me) )
                set("first_landie", 1, me);

        env = environment(me);
        // 初始化藍蝶仙子
        landie = new("/kungfu/class/misc/landie-xianzi");
        // 隨機選擇當前房間一名玩家
        obs = all_inventory(env);
        obs = filter_array(obs, (: userp($1) :));
        
        if (! sizeof(obs))return notify_fail("沒有找到玩家！\n");

        wanjia = obs[random(sizeof(obs))];      
        if( !objectp(obs) ) return 1;
        landie->init_me(me, wanjia);
        landie->move(env);
        
        set("mylandie", landie, me);

        msg += HIY "\n$n" HIY "凝神觀望，似乎看破了藍蝶仙子的破綻。\n" NOR;
        
        message_vision(sort_msg(msg), me, wanjia);
        
        return 1;
}
