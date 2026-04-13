#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Library
{










namespace Library.SystemModels
{
    class MapRegion : DBObject
    {
        [IsIdentity]
        [Association("Regions")]
        public MapInfo Map
        {
            get { return _Map; }
            set
            {
                if (_Map == value) return;

                var oldValue = _Map;
                _Map = value;

                OnChanged(oldValue, value, "Map");
};
};
        private MapInfo _Map;

        [IsIdentity]
        public std::string Description
        {
            get { return _Description; }
            set
            {
                if (_Description == value) return;

                var oldValue = _Description;
                _Description = value;

                OnChanged(oldValue, value, "Description");
};
};
        private std::string _Description;

        [JsonIgnore]
        public BitArray BitRegion
        {
            get { return _BitRegion; }
            set
            {
                if (_BitRegion == value) return;

                var oldValue = _BitRegion;
                _BitRegion = value;

                OnChanged(oldValue, value, "BitRegion");
};
};
        private BitArray _BitRegion;

        public Point[] PointRegion
        {
            get { return _PointRegion; }
            set
            {
                if (_PointRegion == value) return;

                var oldValue = _PointRegion;
                _PointRegion = value;

                OnChanged(oldValue, value, "PointRegion");
};
};
        private Point[] _PointRegion;

        [JsonIgnore]
        [IgnoreProperty]
        public std::string ServerDescription => $"{Map?.Description} - {Description}";

        public RegionType RegionType
        {
            get { return _RegionType; }
            set
            {
                if (_RegionType == value) return;

                var oldValue = _Size;
                _RegionType = value;

                OnChanged(oldValue, value, "RegionType");
};
};
        private RegionType _RegionType;

        public int32_t Size
        {
            get { return _Size; }
            set
            {
                if (_Size == value) return;

                var oldValue = _Size;
                _Size = value;

                OnChanged(oldValue, value, "Size");
};
};
        private int32_t _Size;

        [JsonIgnore]
        public std::vector<Point> PointList;

        public HashSet<Point> GetPoints(int32_t width)
        {
            HashSet<Point> points = new HashSet<Point>(); 

            if (BitRegion != null)
            {
                for (int32_t i = 0; i < BitRegion.Length; i++)
                {
                    if (BitRegion[i])
                        points.Add(new Point(i % width, i / width));
};
};
            else if (PointRegion != null)
            {
                foreach (Point p in PointRegion)
                    points.Add(p);
};

            return points;
};
        public void CreatePoints(int32_t width)
        {
            PointList  = new std::vector<Point>();

            if (BitRegion != null)
            {
                if (width == 0) return;

                for (int32_t i = 0; i < BitRegion.Length; i++)
                {
                    if (BitRegion[i])
                        PointList.Add(new Point(i % width, i / width));
};
};
            else if (PointRegion != null)
            {
                foreach (Point p in PointRegion)
                    PointList.Add(p);
};

};
};
};

}
