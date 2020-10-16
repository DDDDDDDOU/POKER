import { shallowMount, createLocalVue, mount } from "@vue/test-utils";
import ElementUI from "element-ui";
import issue from "../../src/components/issue";


const localVue = createLocalVue();
localVue.use(ElementUI);

const axios = {
    get: async () => "success",
    post:async ()=> "success"


};

/**
 * mock的axios
 * 可以根据需要添加其他函数功能
 */




describe("init",  () => {
    const wrapper = shallowMount(issue, {
        mocks: {
            axios,
        },
        localVue
    });
    it("init state",  () => {

        /**
         * 检查data的初始状态
         */
        expect(wrapper.vm.size).toEqual(0);
        expect(wrapper.vm.blogs).toEqual([]);

    });

    it("test function",()=>{
        wrapper.setData({
            blogs:[{id:1},{id:2}],
            size:2
        });
        expect(wrapper.vm.showMore()).toEqual(1);
        expect(wrapper.vm.remove(1)).toEqual(1);
        expect(wrapper.vm.getBlogs()).resolves.toBeTruthy();
    })



});








