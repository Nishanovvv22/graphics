# 📦 Open Asset Import Library (assimp)

[**assimp**](https://github.com/assimp/assimp)는 그래픽스 프로그래밍에서 장면(scene) 구성에 필요한 다양한 에셋(예: 삼차원 모델, 텍스처 등)을 손쉽게 불러오고(import), 저장하고(export) 변환하는 기능을 제공하는 **C/C++ 라이브러리**입니다.

본 프로젝트에서는 **Assimp 개발자용 라이브러리**를 이용하여 3D 모델 데이터를 불러오고 렌더링에 활용합니다. 따라서, 프로그램을 빌드하기 전에 아래 명령어를 실행하여 **`libassimp-dev` 패키지를 설치**해야 합니다.

---

## 🖥️ Ubuntu에서 설치하기  

Ubuntu 환경에서는 다음 명령어를 실행하여 `libassimp-dev` 패키지를 설치할 수 있습니다:

```bash
sudo apt install libassimp-dev
```

설치가 완료되면 `pkg-config`를 이용하여 Assimp 라이브러리가 정상적으로 설치되었는지 확인할 수 있습니다:

```bash
pkg-config --modversion assimp
```

위 명령어를 실행했을 때 **버전 정보(예: 5.2.5)**가 출력되면 설치가 정상적으로 완료된 것입니다. 🚀

---

✅ **이제 Assimp를 활용하여 프로젝트를 빌드할 준비가 되었습니다!**

