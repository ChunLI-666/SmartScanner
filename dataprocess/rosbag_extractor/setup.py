from setuptools import setup, find_packages

setup(
    name='rosbag_extractor',
    version='0.1.0',
    packages=find_packages(),
    install_requires=[
        'opencv-python',
        'open3d',
        'pycryptodomex',
        'python-gnupg',
        'rospkg',
        'tqdm',
        'loguru',
    ],
    entry_points={
        'console_scripts': [
            'image_extractor=rosbag_extractor.extract_images:main',
            'point_cloud_extractor=rosbag_extractor.extract_pcds:main',
        ],
    },
)
