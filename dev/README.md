# 🛠️ 개발 정보  

💡 **공식 운영체제:** Ubuntu LTS 18.04+  
⚠️ **비공식 운영체제:** Windows, Mac, 기타 Linux 배포판  

> ⚠️ **주의:** 비공식 운영체제에 대해서 본 교과목은 **공식적인 기술 지원을 제공하지 않습니다.**  

---

## 🌍 비공식 운영체제에서 가상 환경으로 개발하기  

비공식 운영체제에서 **Ubuntu LTS 18.04+**를 사용하는 가장 쉬운 방법은 **가상 머신(VM)**을 이용하는 것입니다.  

✅ **추천 방법:**  
- [VirtualBox](https://www.virtualbox.org/) 또는 [VMWare](https://www.vmware.com/)를 이용해 Ubuntu를 설치  
- 현재 사용 중인 운영체제(**Host OS**) 위에 **Ubuntu LTS 18.04+ (**Guest OS**)를 실행  
- 과제 수행을 위한 **가장 간단하고 안정적인 방법**  

> 💡 **비공식 운영체제를 사용 중이라면, 가상 환경을 활용하는 것이 가장 권장됩니다.**  

---

## 💻 비공식 운영체제에서 직접 개발하기  

비공식 운영체제에서도 개발할 수 있는 정보를 제공합니다.  
그러나 **최종 평가는 공식 운영체제(Ubuntu LTS 18.04+)에서 빌드 및 실행된 결과물로 진행**됩니다.  

### 🖥️ Windows 환경  
🔹 **MinGW**  
- **MSYS2 + MinGW**를 활용한 Windows 네이티브 개발 환경  
- X Server 없이 Windows에서 OpenGL 프로그램 실행 가능  
- [설치 및 사용법](https://github.com/kmuvcl/kmuvcl/blob/master/dev/GCC%20with%20MinGW%20(%2B%20OpenGL).md) 참고  

🔹 **WSL2 (Windows Subsystem for Linux)**  
- Windows에서 Linux 배포판을 실행하는 방식  
- **설치 방법:**  
  1. Microsoft Store에서 **Ubuntu LTS 최신 배포판** 설치  
  2. [WSL2 설치 가이드](https://learn.microsoft.com/en-us/windows/wsl/install) 참고  
  3. OpenGL 프로그램을 실행하려면 [VcXsrv Windows X Server](https://sourceforge.net/projects/vcxsrv/) 설치  

### 🍏 Mac 환경  
🔹 **Intel Mac & Apple Silicon (M1, M2) 지원**  
- **가장 추천하는 방법:**  
  - [VMware](https://www.vmware.com/)를 이용해 Ubuntu LTS 18.04+ 설치  
  - 안정적인 성능과 높은 호환성 제공  

---

## 📢 추가 안내  
- 과제 및 실습 환경 구축이 어려운 경우, **조교 또는 동료들과 소통하며 해결**하는 것을 추천합니다.  
- 공식 운영체제(Ubuntu LTS 18.04+)에서의 개발을 우선으로 고려하세요.  

🚀 **원활한 개발 환경 구축을 바랍니다!** 😊  
