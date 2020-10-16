import { shallowMount, createLocalVue, } from "@vue/test-utils";
import ElementUI from "element-ui";
import topnav from "../../src/components/topnav";


const localVue = createLocalVue();
localVue.use(ElementUI);

const axios = {
    get: async () => "success",
    post:async ()=> "success"}
;

const $router = {
    push: jest.fn()
    // ... 其他属性
}
const $root ={
    logout:jest.fn(),



}
/**
 * mock的axios
 * 可以根据需要添加其他函数功能
 */

// const Mock=require('mockjs');
// Mock.mock('http://localhost:8088/user/reg',()=>{
//     return ({
//         data:"success"
//     })
//     }
// )

describe("init",  () => {
    const wrapper = shallowMount(topnav, {
        mocks: {
            axios
        },
        localVue
    });
    it("init state",  () => {


        /**
         * 检查data的初始状态
         */
        expect(wrapper.vm.heat).toEqual([
            {value: "三全鲜食（北新泾店）", type: '话题', id: 1},
            {value: "Hot honey 首尔炸鸡", type: '话题', id: 2},
            {value: "新旺角茶餐厅", type: '话题', id: 3},
            {value: "泷千家(天山西路店)", type: '话题', id: 4},
            {value: "胖仙女纸杯蛋糕", type: '话题', id: 5},
            {value: "贡茶", type: '话题', id: 6},
            {value: "豪大大香鸡排超级奶爸", type: '话题', id: 7},
            {value: "茶兰（奶茶，手抓饼）", type: '话题', id: 8}
        ]);
        expect(wrapper.vm.dialogVisible).toEqual(false);
        expect(wrapper.vm.activeIndex).toEqual('1');
        expect(wrapper.vm.activeIndex2).toEqual('1');
        expect(wrapper.vm.timeout).toEqual(null);
        expect(wrapper.vm.state).toEqual('');
        // expect(wrapper.vm.loadAll()).resolves.toBeTruthy();

    });


});

describe("test searchbar",()=>{
    const wrapper = shallowMount(topnav, {
        mocks: {
            axios,
            $router,
            $root
        },
        localVue
    });
    it("test querySearchAsync", ()=>{
        wrapper.setData({state:""});
        expect(wrapper.vm.querySearch()).toEqual(false)
        wrapper.setData({state:"三"});
        expect(wrapper.vm.querySearchAsync("三",()=>{return 10})).toEqual([]);
        expect(wrapper.vm.querySearchAsync("",()=>{return 10})).toEqual([
            {value: "三全鲜食（北新泾店）", type: '话题', id: 1},
            {value: "Hot honey 首尔炸鸡", type: '话题', id: 2},
            {value: "新旺角茶餐厅", type: '话题', id: 3},
            {value: "泷千家(天山西路店)", type: '话题', id: 4},
            {value: "胖仙女纸杯蛋糕", type: '话题', id: 5},
            {value: "贡茶", type: '话题', id: 6},
            {value: "豪大大香鸡排超级奶爸", type: '话题', id: 7},
            {value: "茶兰（奶茶，手抓饼）", type: '话题', id: 8}
        ]);
    });
    it("test handleSelect",()=>{
        expect(wrapper.vm.handleSelect({type:'用户',id:'18796700152',mock:false})).toEqual('visit');
        expect(wrapper.vm.handleSelect({type:'用户',id:'18796700152',mock:true})).toEqual('person');
        expect(wrapper.vm.handleSelect({type:'话题',id:'18796700152',mock:true})).toEqual('discover');
        expect(wrapper.vm.handleSelect({type:'话题',id:'18796700152',mock:false})).toEqual({type:'话题',id:'18796700152',mock:false});
    });
    it("test log(i)",()=>{
        expect(wrapper.vm.log(0)).toEqual(0);
        expect(wrapper.vm.log(1)).toEqual(1);
        expect(wrapper.vm.log(2)).toEqual(2);
        expect(wrapper.vm.log(3)).toEqual(-1);
    })
})


// describe("log switch ",()=>{
//     const wrapper = shallowMount(topnav, {
//         mocks: {
//             axios,
//             $router,
//             $root
//         },
//         localVue
//     });
//
//     it("log function",()=>{
//         expect(wrapper.vm.log(0)).toEqual(0);
//         expect(wrapper.vm.log(1)).toEqual(1);
//         expect(wrapper.vm.log(2)).toEqual(2);
//         expect(wrapper.vm.log(3)).toEqual(-1);
//     })
//
//
// })

