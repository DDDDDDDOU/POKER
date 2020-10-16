import { shallowMount, createLocalVue, mount } from "@vue/test-utils";
import ElementUI from "element-ui";
import signinForm from "../../src/components/signinForm";


const localVue = createLocalVue();
localVue.use(ElementUI);

/**
 * mock的axios
 * 可以根据需要添加其他函数功能
 */
const axios = {
  get: async () => "success",
  post:async ()=>"success"
};

const $router = {
  push: jest.fn()
  // ... 其他属性
}
describe("init", () => {
  it("init state", () => {
    const wrapper = shallowMount(signinForm, {
      mocks: {
        axios
      },
      localVue
    });

     /**
     * 检查data的初始状态
     */
     expect(wrapper.vm.error_message).toEqual("");
    expect(wrapper.vm.checked).toEqual(false);
    expect(wrapper.vm.isSubmit).toEqual(false);
    expect(wrapper.vm.login_path).toEqual(1);
    expect(wrapper.vm.form).toEqual( {
      phone: '',
      password: '',
    });


  });
});


describe("signinForm", ()=>{
  const wrapper = mount(signinForm, {
    mocks: {
      axios
    },
    localVue
  });


    it("input loginFrom text", () => {
    /**
     * 找到输入框
     */
    const input_phone = wrapper.find("#signinForm_input_phone");
    const input_password = wrapper.find("#signinForm_input_password");

    expect(input_phone.exists()).toBe(true);
    expect(input_password.exists()).toBe(true);
    /**
     * 修改输入的值，检查绑定的变量calculateText是否发生改变
     */
    input_phone.setValue("18796700152");
    input_password.setValue("12345678");
    expect(wrapper.vm.form.phone).toEqual("18796700152");
    expect(wrapper.vm.form.password).toEqual("12345678");

  });


});

describe("login and axios " , ()=>{
      const wrapper = mount(signinForm, {
      mocks: {
        axios,
        $router
      },
      localVue
    });
  it("login",   () => {

    expect(wrapper.vm.isSubmit).toEqual(false);
    expect(wrapper.vm.onSubmit()).toEqual(false);
    expect(wrapper.vm.isSubmit).toEqual(false);
      wrapper.setData({
          form:{
              phone:"",
              password:"12345678"
          }
      });
      expect(wrapper.vm.onSubmit()).toEqual(false);


      wrapper.setData({
          form:{
              phone:"111111111111",
          }
      });
      expect(wrapper.vm.onSubmit()).toEqual(false);

      wrapper.setData({
          form:{
              phone:"18796700152",
              password:""
          }
      });
      expect(wrapper.vm.onSubmit()).toEqual(false);


      wrapper.setData({
          form:{
              phone:"18796700152",
              password:"11"
          }
      });
      expect(wrapper.vm.onSubmit()).toEqual(false);


      wrapper.setData({
          form:{
              phone:"18796700152",
              password:"12345678"
          }
      });
      expect(wrapper.vm.onSubmit()).resolves.toBeTruthy();


    wrapper.setData({
      isSubmit:true
    })
    expect(wrapper.vm.onSubmit()).toEqual(false);
    /**
     * 需要等待下一次渲染后，才能检查DOM的变化
     */

  });


  it("btn clicked",async ()=>{
      wrapper.setData({
          isSubmit:false
      })
      expect(wrapper.vm.isSubmit).toEqual(false);
    const btn = wrapper.find("#signinForm_button_login");
    expect(btn.exists()).toBe(true);
    await btn.trigger('click');
    expect(wrapper.vm.isSubmit).toEqual(true);
  });


  it("go to sign up",()=>{
    expect(wrapper.vm.signup()).toBeTruthy();
  });


  it("handleselect",()=>{
      expect(wrapper.vm.login_path).toEqual(1);
      expect(wrapper.vm.handleSelect(2)).toEqual(true);
      expect(wrapper.vm.login_path).toEqual(2);
  })
});

// describe("router-link",()=>{
//   const router = new VueRouter({ routes });
//   const wrapper = mount(signinForm, {
//     mocks: {
//       axios
//     },
//     localVue
//   });
//   const wrapper2=shallowMount(App,{
//     localVue,
//     router
//   })
//   it('sign up btn',async ()=>{
//     const btn = wrapper.find("#signinForm_button_signup");
//     expect(btn.exists()).toBe(true);
//     await btn.trigger("click");
//     expect(wrapper2.find())
//   })
// });
//



